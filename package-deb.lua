require("lbuild")

local path = "/home/zaphod/Workspace/bristolgui/Packaging/"

lbuild.build(path)
lbuild.deb_create(path, "bristolgui", "debian.config")
--lbuild.deb_clean(path)