main.out : main.cpp custommdspi.cpp makefile
	g++ -o main.out main.cpp custommdspi.cpp \
		./CTP_API_64/libthostmduserapi.so \
		-I./CTP_API_64/ \

clean :
	rm DialogRsp.con QueryRsp.con TradingDay.con main.out
