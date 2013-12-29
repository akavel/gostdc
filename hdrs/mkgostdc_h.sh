#!/bin/bash
cd $(dirname "$0")
cat ../gostdc.h.head > ../gostdc.h
grep '#include' ../*.c ./*.h ./sys/*.h |  # find out all included headers from all *.c and *.h
	sed 's#^\.*/\(.*\):.*[<"]\(.*\)[">].*#\2 \1#g' |  # prepare dependency format for 'tsort'
	tsort |               # reorder based on dependency information
	grep -v '.c$' |       # we needed .c files only to force full list of .h files - strip them now
	\
	grep -v -x 'bsd.h' |  # drop some headers we shouldn't need
	grep -v -x 'fcntl.h' |
	grep -v -x 'unistd.h' |
	\
	xargs cat |           # concatenate all headers together in correct order
	grep -v '#pragma' |
	grep -v '#include' |  # we already have all headers in this one file
	cat >> ../gostdc.h    # write result to gostdc.h
cat ../gostdc.h.tail >> ../gostdc.h
