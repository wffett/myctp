main.out : main.cpp custommdspi.cpp makefile
	g++ -std=c++11 -o main.out main.cpp custommdspi.cpp \
		./CTP_API_64/libthostmduserapi.so \
		-I./CTP_API_64/ \

clean :
	rm DialogRsp.con QueryRsp.con TradingDay.con main.out
