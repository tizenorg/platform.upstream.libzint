# Make libzint and zint together

zint:
	$(MAKE) -C backend/

install:
	$(MAKE) install -C backend/

uninstall:
	$(MAKE) uninstall -C backend/

clean:
	$(MAKE) clean -C backend/

