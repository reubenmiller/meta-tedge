do_install:append () {
    install -d "${D}${systemd_system_unitdir}"
    install -m 0644 "${S}/configuration/init/systemd/tedge-agent.service" "${D}${systemd_system_unitdir}"

    install -d "${D}${sysconfdir}/tedge-postinsts"
    install -m 0755 "${S}/configuration/package_scripts/_generated/tedge-agent/deb/postinst" "${D}${sysconfdir}/tedge-postinsts/"
    mv "${D}${sysconfdir}/tedge-postinsts/postinst" "${D}${sysconfdir}/tedge-postinsts/4-tedge-agent"
}

do_package:prepend () {
    work_dir = "%s"%(d.getVar('WORKDIR', True))
    package_name = "%s"%(d.getVar('PN', True))

    prerm_path = "%s/git/configuration/package_scripts/_generated/tedge-agent/deb/prerm"%(work_dir)
    postrm_path = "%s/git/configuration/package_scripts/_generated/tedge-agent/deb/postrm"%(work_dir)

    with open(prerm_path, "r") as prerm:
        d.appendVar("pkg_prerm:%s"%(package_name), prerm.read())
        
    with open(postrm_path, "r") as postrm:
        d.appendVar("pkg_postrm:%s"%(package_name), postrm.read())
}

FILES:tedge-agent += "${systemd_system_unitdir}/tedge-agent.service"
