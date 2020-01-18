cd /home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug
echo -n > 5;echo -n  > 15;echo -n  > 20
cd -
for cit in '5' '15' '20';do
# for cit in '20';do
	for x in `seq 1 10`; do
	# for x in `seq 1 10`; do
		./randomCitiesGenerator.py ${cit}
		mv testData${cit}.txt /home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug/testDataX.txt
		cd /home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug
		/home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug/genetic testDataX.txt 100 100 > logs
		true=`cat logs | grep finalWeight | head -1 | sed 's/.*=//g'`
		actuall=`cat logs | grep finalWeight | tail -1 | sed 's/.*=//g'`
		stat=$((true*100/actuall))%
		time=`cat logs | grep nanoseconds | sed 's/.*: *//g'`
		echo "$stat:$time" >> $cit
		# echo "$time"
		cat logs
		cd -
	done
done