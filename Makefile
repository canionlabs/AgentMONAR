
upload:
	@echo "Build BIN"
	pio run
	@echo "Upload new firmware"
	curl -v -F file=@./.pioenvs/esp12e/firmware.bin --insecure -u admin@blynk.cc:admin https://blynk.canionlabs.io:9443/admin/ota/start
