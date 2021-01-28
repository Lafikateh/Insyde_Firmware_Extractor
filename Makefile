all:
	$(CC) -std=c99 -Os -s -o Insyde_Firmware_Extractor Main.c Files.c Strings.c

release:
	$(CC) -std=c99 -Os -s -o Insyde_Firmware_Extractor Main.c Files.c Strings.c

debug:
	$(CC) -std=c99 -g3 -o Insyde_Firmware_Extractor Main.c Files.c Strings.c

clean:
	$(RM) $(OBJS) $(OUT)
