#!/usr/bin/env bash
echo -n > dynamicSummary
echo -n > bruteforceSummary
for file in `ls | grep logs | sort --version-sort`;do
	nr=`echo $file | sed 's/logs//g'`
	dynamic=`cat $file | grep nanoseconds | head -1 | sed 's/.*: //g'`
	echo "${nr} miast: ${dynamic}ns" >> dynamicSummary
	if [[ `cat $file | grep nanoseconds | wc -l` > 1 ]];then
		bruteforce=`cat $file | grep nanoseconds | tail -1 | sed 's/.*: //g'`
		echo "${nr} miast: ${bruteforce}ns" >> bruteforceSummary
	fi
done