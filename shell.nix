{ pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
  # Is this cheating? I think it is.
  # (i should definitely *not* be doing this)
  nativeBuildInputs = pkgs.dwm.buildInputs;
}
