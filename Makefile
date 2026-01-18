@PHONY: help build debug check verbose-check build-upload upload-and-teleplot

help:
	@echo "Makefile commands:"
	@echo "  build               - Build the project"
	@echo "  debug               - Build the project and open debugger"
	@echo "  check               - Run code checks"
	@echo "  verbose-check       - Run code checks but with verbose output"
	@echo "  build-upload        - Build and upload the project"
	@echo "  upload-and-monitor  - Build, upload and watch serial port"
	@echo "  upload-and-teleplot - Build, upload and start the teleplot redirect script"

build:
	@echo "Starting to build project"
	pio run

check:
	@echo "Running static checks"
	pio check --skip-packages

debug:
	@echo "Enter debugging"
	pio debug --interface gdb

verbose-check:
	@echo "Running static checks with verbose output"
	pio check -v --skip-packages

build-upload:
	@echo "Televersing the program"
	pio run -t upload -e nucleo_h723zg_BreizhBot
	@echo "Upload complete"

upload-and-monitor:
	@echo "Televersing the program then use pio built-in serial monitor"
	pio run -t upload -t monitor -e nucleo_h723zg_BreizhBot

upload-and-teleplot: build-upload
	@echo "Upload complete"
	python scripts/teleplot_link.py