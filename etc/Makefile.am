
dist_sysconf_DATA = quadrature.tar.xz

QUADRATUREARCHIVE = quadrature.tar.xz

install-data-hook:
	cd $(DEF_SYSCONFDIR); \
	tar -tvf $(QUADRATUREARCHIVE) > uninstall_manifest.txt; \
	mkdir quadrature; \
	tar xvfJ $(QUADRATUREARCHIVE) -C./quadrature; \
	cd quadrature; \
	sed -i '1d' ../uninstall_manifest.txt; \
	cat ../uninstall_manifest.txt | sed --expression='s/.*. //' | xargs chmod 444;

uninstall-local:
    cd $(DEF_SYSCONFDIR); \
    cd quadrature; \
    cat ../uninstall_manifest.txt | sed --expression='s/.*. //' | xargs rm --force; \
	cd $(DEF_SYSCONFDIR); \
    rm --force uninstall_manifest.txt;
