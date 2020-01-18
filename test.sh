cit=15
cd /home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug
echo -n > 1;echo -n  > 2;echo -n  > 3
cd -
for x in `seq 1 100`; do
	./randomCitiesGenerator.py ${cit}
	mv testData${cit}.txt /home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug/testDataX.txt
	cd /home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug
	/home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug/genetic testDataX.txt 100 100 > logs
	true=`cat logs | grep finalWeight | head -1 | sed 's/.*=//g'`
	actuall=`cat logs | grep finalWeight | tail -1 | sed 's/.*=//g'`
	echo $((true*100/actuall))% >> 1
	time=`cat logs | grep nanoseconds | sed 's/.*: *//g'`
	cat logs

	/home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug/genetic testDataX.txt 100 10 > logs
	true=`cat logs | grep finalWeight | head -1 | sed 's/.*=//g'`
	actuall=`cat logs | grep finalWeight | tail -1 | sed 's/.*=//g'`
	echo $((true*100/actuall))% >> 2
	time=`cat logs | grep nanoseconds | sed 's/.*: *//g'`
	cat logs

	/home/kuba/workspace/pea/qt/build-genetic-Desktop_Qt_5_7_0_GCC_64bit-Debug/genetic testDataX.txt 10 100 > logs
	true=`cat logs | grep finalWeight | head -1 | sed 's/.*=//g'`
	actuall=`cat logs | grep finalWeight | tail -1 | sed 's/.*=//g'`
	echo $((true*100/actuall))% >> 3
	time=`cat logs | grep nanoseconds | sed 's/.*: *//g'`
	cat logs

 	cd -
done