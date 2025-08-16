{ pkgs }: {
	deps = [
   pkgs.tk
   pkgs.tcl
   pkgs.qhull
   pkgs.gtk3
   pkgs.gobject-introspection
   pkgs.ghostscript
   pkgs.freetype
   pkgs.ffmpeg-full
   pkgs.cairo
   pkgs.xsimd
   pkgs.pkg-config
   pkgs.libxcrypt
   pkgs.python312Packages.matplotlib
   pkgs.python311Packages.scipy
   pkgs.python311Packages.numpy
		pkgs.clang
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}