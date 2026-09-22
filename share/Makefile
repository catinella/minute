
ifeq ($(filter clean cleanall,$(MAKECMDGOALS)),)
ifndef PREFIX
$(error PREFIX symbol undefined)
endif
endif

VERSION ?= unknown

all:		minuteC.pc minuteCPP.pc

%.pc:		%.pc.template
		@echo "[ SED ] $@"
		@sed -e 's:##PREFIX##:$(PREFIX):' -e 's/##VERSION##/$(VERSION)/' $< > $@

clean:
		@echo "[CLEAN]"
		@rm -fv minuteC*.pc

cleanall:	clean
