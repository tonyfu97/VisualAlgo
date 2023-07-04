all:
	for d in src tests; \
	do \
		$(MAKE) -j --directory=$$d all; \
	done

clean:
	$(MAKE) -j -C src clean
	$(MAKE) -j -C tests clean
