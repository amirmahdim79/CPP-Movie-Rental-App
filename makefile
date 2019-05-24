CC := g++

all: a.out

a.out: main.o exceptions.o program.o user.o customer.o publisher.o movie.o notification.o money.o rate.o comment.o reply.o admin.o
	$(CC) main.o exceptions.o program.o user.o customer.o publisher.o movie.o notification.o money.o rate.o comment.o reply.o admin.o -o a.out

main.o: program.h main.cpp
	$(CC) -c main.cpp

exceptions.o: exceptions.h exceptions.cpp
	$(CC) -c exceptions.cpp

program.o: program.h exceptions.h user.h customer.h publisher.h movie.h notification.h money.h rate.h comment.h reply.h program.cpp
	$(CC) -c sphere.cpp

user.o: user.h movie.h notification.h user.cpp
	$(CC) -c user.cpp

customer.o: customer.h user.h customer.cpp
	$(CC) -c customer.cpp

publisher.o: publisher.h user.h movie.h publisher.cpp
	$(CC) -c publisher.cpp

movie.o: movie.h rate.h comment.h movie.cpp
	$(CC) -c movie.cpp

notification.o: notification.h notification.cpp
	$(CC) -c notification.cpp

money.o: money.h movie.h money.cpp
	$(CC) -c money.cpp

rate.o: rate.h rate.cpp
	$(CC) -c rate.cpp

comment.o: comment.h reply.h comment.cpp
	$(CC) -c comment.cpp

reply.o: reply.h reply.cpp
	$(CC) -c reply.cpp

admin.o: admin.h program.h admin.cpp
	$(CC) -c admin.cpp

.PHONY: clean
clean:
	rm -r *.o
	rm -r *.out