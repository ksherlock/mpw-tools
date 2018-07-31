#!/usr/bin/env ruby -w

# process the flags.yaml file
# and generate a flags.h and flags.c file.
#

#
# todo -- support for long-options (--longoption, --longoption=value, etc)
#
#

require 'erb'
require 'yaml'

header_preamble = <<EOF

#ifndef __flags_h__
#define __flags_h__

typedef struct Flags {
EOF

header_postamble = <<EOF
} Flags;


extern struct Flags flags;

int FlagsParse(int argc, char **argv);

void FlagsHelp(void);

#endif

EOF


class Option
	@@map = {
		# some of these are a bad idea but whatever...
		'>' => 'gt',
		'<' => 'lt',
		',' => 'comma',
		'.' => 'period',
		'/' => 'forward_slash',
		'\\' =>  'back_slash',
		'?' => 'question',
		'|' => 'pipe',
		'~' => 'tilde',
		'`' => 'grave',
		'!' => 'bang',
		'@' => 'at',
		'#' => 'hash',
		'$' => 'dollar',
		'%' => 'percent',
		'^' => 'caret',
		'&' => 'ampersand',
		'*' => 'star',
		'(' => 'left_paren',
		')' => 'right_paren',
		'-' => 'minus',
		'+' => 'plus',
		'=' => 'equal',
		'[' => 'left_bracket',
		']' => 'right_bracket',
		'{' => 'left_brace',
		'}' => 'right_brace',
		':' => 'colon',
		';' => 'semi_colon',
		'\'' => 'apostrophe',
		'"' => 'quote'
	}

	def initialize(hash)

		@char = hash['char'].to_s
		@argument = hash['argument'] || false

		@flag_name = hash['flag_name']
		@flag_name = @flag_name.to_s if @flag_name

		@xor = hash['xor'] || []
		@xor = case @xor
		when Array
			@xor
		when Integer, String
			[ @xor ]
		else
			raise "Invalid xor type: #{@xor}"
		end

		@xor.map! { |x| x.to_s }
	end

	attr_reader :char, :xor, :argument

	def flag_name
		return @flag_name if @flag_name
		return self.class.flag_name(@char)
	end

	def self.flag_name(char)
		return '_' + @@map[char] if @@map[char] 
		return '_' + char
	end


end

# better ARGF.
def argf_each 

	if ARGV.count > 0

		ARGV.each {|file|

			File.open(file, "r") {|io| 
				yield file, io 
			}
		}

	else
		yield nil, $stdin
	end

end


def escape_cstr(x)

	# escape a c string

	x.gsub(/([\\"])/, "\\\\1")
end


code = ERB.new(DATA.read(), 0, "%<>")

argf_each {|filename, file|


	data = YAML.load(file)

	help = data['help']
	options = data['options']
	case_insensitive = data['case_insensitive'] || false
	name = data['name'] || ''

	# prevent warnings for unused vars.
	options = options
	help = help
	case_insensitive = case_insensitive
	name = name

	# options is an array of items which may be hashes, strings, or numbers.
	# normalize them.

	options = options.map {|opt|

		opt = case opt
		when String, Integer
			{ 'char' => opt }
		when Hash
			# {'o' => { ... }}
			# or
			# {'char' => , ... }
			if opt['char']
				opt
			else
				opt = opt.first
				opt[1].merge({ 'char' => opt[0] })
			end
		else
			raise "Unexpected data type: #{opt}"
		end

		Option.new(opt)
	}

	if case_insensitive
		options.each {|opt|
			opt.char.downcase!
		}
	end

	#data[options] = options
	# check for help?

	basename = filename
	basename = $1 if filename && filename =~ /^(.*)\./

	b = binding # bind help, options for ERB.

	#io = $stdout;
	io = basename ? File.open(basename + ".c", "w") : $stdout
	#io = File.open(basename + ".c", "w") unless basename.nil?
	io.write(code.result(b))
	
	io.close unless io == $stdout


	io = basename ? File.open(basename + ".h", "w") : $stdout
	io.write(header_preamble)
	# two passes - one with arguments, one without.
	options.each {|opt|
		if opt.argument
			io.printf("    char *%s;\n", opt.flag_name)
		end
	}
	io.puts()
	options.each {|opt|
		if !opt.argument
			io.printf("    unsigned %s:1;\n", opt.flag_name)
		end
	}
	io.puts

	io.write(header_postamble)
	io.close unless io == $stdout


#	#puts options.to_yaml
#	puts code.result(binding())

}


__END__

#ifdef __ORCAC__
#pragma optimize 79
#pragma noroot
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "<%= basename ? basename + '.h' : '' %>"

void FlagsHelp(void)
{
% help.each do |h|
  fputs("<%= escape_cstr(h) %>\n", stdout);
% end
  fputs("\n", stdout);
  exit(0);
}

struct Flags flags;
int FlagsParse(int argc, char **argv)
{
  char *cp;
  char *optarg;

  char c;
  int i;
  int j;
  int eof; // end-of-flags
  int mindex; // mutation index.

  memset(&flags, 0, sizeof(flags));

  for (i = 1, mindex = 1, eof = 0; i < argc; ++i)
  {    
    cp = argv[i];
    c = cp[0];
      
    if (c != '-' || eof)
    {
      if (i != mindex) argv[mindex] = argv[i];
      mindex++;
      continue;    	
    }
      
    // -- = end of options.
    if (cp[1] == '-' && cp[2] == 0)
    {
      eof = 1;
      continue;
    }
   
    // now scan all the flags in the string...
    optarg = NULL;
    for (j = 1; ; ++j)
    {          
      c = cp[j];
      if (c == 0) break;
          
      switch (c)
      {
% if help && !options.find_index {|x| x.char == 'h' } 
      case 'h':
        FlagsHelp();
        exit(0);
% end            
% #
% options.each do |opt|
      case '<%= escape_cstr(opt.char) %>':
% if case_insensitive && opt.char =~ /^[a-z]$/
      case '<%= escape_cstr(opt.char.upcase) %>':
% end
% # check for an argument.
% flag_name = 'flags.' + opt.flag_name
% #
% if opt.argument
        // -xarg or -x arg
        ++j;  
        if (cp[j])
        {
          optarg = cp + j;
        }
        else
        {
          if (++i >= argc)
          {
            fputs("### <%= name %> - \"-<%= opt.char %>\" requires an argument.\n", stderr); 
            exit(1);
          }
          optarg = argv[i];
        }
        <%= flag_name %> = optarg;

% else # no argument.
        <%= flag_name %> = 1;
% end # if no argument.
% #
% # unset any exclusive or values
% opt.xor.each do |xor_opt|
        flags.<%= Option.flag_name(xor_opt) %> = 0;
%end
        break;
% end # options.each

      default:
        fprintf(stderr, "### <%= name %> - \"-%c\" is not an option.\n", c);
        exit(1); 
      }
            
      if (optarg) break;
    }    
  }

  return mindex;
}
