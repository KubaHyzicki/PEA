 #!/usr/bin/env bash
echo -n > geneticSummary
for file in `ls | grep logs | sort --version-sort`;do
	nr=`echo $file | sed 's/logs//g'`
	dynamic=`cat $file | grep nanoseconds | head -1 | sed 's/.*: //g'`
	echo "${nr} miast: ${dynamic}ns" >> geneticSummary
done