all:
	gcc -std=c99 -Os -s -o Insyde_Firmware_Extractor Main.c Files.c Strings.c

release:
	gcc -std=c99 -Os -s -o Insyde_Firmware_Extractor Main.c Files.c Strings.c

debug:
	gcc -std=c99 -g3 -o Insyde_Firmware_Extractor Main.c Files.c Strings.c

clean:
	rm -f $(OBJS) $(OUT)
