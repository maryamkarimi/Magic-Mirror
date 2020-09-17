CC = g++
CFLAGS = -c
CMATH = -lm
FLAGS = `sdl-config --cflags --libs` -lSDL_ttf -lcurl
CURL = -lcurl


all: clean Test

Test: GreetingUI.o Time.o Reminder.o Weather.o WeatherParser.o WeatherUI.o UI.o Time.o TimeUI.o ReminderUI.o Calendar.o CalendarUI.o
	$(CC) -o $@ $^ $(CMATH) $(FLAGS)

Weather.o: Weather.cpp Weather.h
	$(CC) $(CFLAGS) -o $@ $< $(CURL)

WeatherParser.o: WeatherParser.cpp WeatherParser.h
	$(CC) $(CFLAGS) -o $@ $<

WeatherUI.o: WeatherUI.cpp WeatherUI.h
	$(CC) $(CFLAGS) -o $@ $<

Reminder.o: Reminder.cpp Reminder.h
	$(CC) $(CFLAGS) -o $@ $<

ReminderUI.o: ReminderUI.cpp ReminderUI.h
	$(CC) $(CFLAGS) -o $@ $<

CalendarUI.o: CalendarUI.cpp CalendarUI.h
	$(CC) $(CFLAGS) -o $@ $<

UI.o: UI.cpp UI.h
	$(CC) $(CFLAGS) -o $@ $<

Time.o: Time.cpp Time.h
	$(CC) $(CFLAGS) -o $@ $<

TimeUI.o: TimeUI.cpp TimeUI.h
	$(CC) $(CFLAGS) -o $@ $<

Calendar.o: Calendar.cpp Calendar.h
	$(CC) $(CFLAGS) -o $@ $<

Greeting.o: GreetingUI.cpp GreetingUI.h
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -f *.o Test
