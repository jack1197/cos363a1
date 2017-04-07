linux:

run build.sh, then the output will be in ./Bin/project, with the required resources copied in.
alternatively, sync.sh will also build and run the project, and will watch for changes in the source code, which will trigger a rebuild/restart

windows:

open solution in visual studio, run in x86 (32 bit) Debug Mode. Other configurations may cause errors due to difficult-to-troubleshoot bugs that I did not have time to fix