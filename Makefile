all:
	@$(CC) -std=c99 -Os -s -o Insyde_Firmware_Extractor Main.c

release:
	@$(CC) -std=c99 -Os -s -o Insyde_Firmware_Extractor Main.c

debug:
	@$(CC) -std=c99 -g3 -o Insyde_Firmware_Extractor Main.c

clean:
	@$(RM) Insyde_Firmware_Extractor
