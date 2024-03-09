{
  description = "A very basic flake";

  inputs = {
    flake-utils.url = github:numtide/flake-utils;
    tree-sitter-scala = {
      url = github:yilinwei/tree-sitter-scala;
      flake = false;
    };
  };

  outputs = { self, nixpkgs, flake-utils, tree-sitter-scala }:
    flake-utils.lib.eachDefaultSystem(system: let
      overlay = (final: prev: {
        tree-sitter = prev.tree-sitter.override {
          extraGrammars = {
            tree-sitter-scala = {
              src = tree-sitter-scala;
              version = "0.20.3.git";
            };
          };
        };
      });
      pkgs = import nixpkgs {
        inherit system;
        overlays = [ overlay ];
      };
      libtree-sitter-scala = with pkgs;
        runCommandNoCCLocal "libtree-sitter-scala" {} ''
            mkdir -p $out/lib
            ln -s -T ${pkgs.tree-sitter-grammars.tree-sitter-scala}/parser $out/lib/libtree-sitter-scala.so
        '';
    in {
      packages = rec {
        tree-sitter-scala = pkgs.tree-sitter-grammars.tree-sitter-scala;
      };
      devShell = pkgs.mkShell {
        packages = with pkgs; [ gcc gnumake tree-sitter pkg-config libtree-sitter-scala ];
      };
    });
}
