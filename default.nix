{ lib
, stdenv
, pkg-config
, xorg
, libXft
, fontconfig
, freetype
}:

stdenv.mkDerivation {
  pname = "dwm-custom";
  version = "local";

  src = ./.;

  nativeBuildInputs = [
    pkg-config
  ];

  buildInputs = [
    xorg.libX11
    xorg.libXinerama
    libXft
    fontconfig
    freetype
  ];

  prePatch = ''
    sed -i "s|/usr/local|$out|g" config.mk
    sed -i "s|^X11INC = .*|X11INC = ${xorg.libX11.dev}/include|g" config.mk
    sed -i "s|^X11LIB = .*|X11LIB = ${xorg.libX11}/lib|g" config.mk
    sed -i "s|^FREETYPEINC = .*|FREETYPEINC = ${freetype.dev}/include/freetype2|g" config.mk
  '';

  installPhase = ''
    runHook preInstall
    mkdir -p $out/bin $out/share/man/man1
    make PREFIX=$out install
    runHook postInstall
  '';

  meta = {
    description = "Custom local dwm build";
    homepage = "https://dwm.suckless.org/";
    license = lib.licenses.mit;
    platforms = lib.platforms.linux;
  };
}
