##
## EPITECH PROJECT, 2020
## OOP_babel_2019
## File description:
## conanfile
##

from conans import ConanFile, CMake

class Conan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "OpenSSL/1.1.1b@conan/stable"

   generators = "cmake", "cmake_find_package", "cmake_paths"
   def configure(self):
       if "shared" in self.options:
           pass
       
   def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin

   def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()