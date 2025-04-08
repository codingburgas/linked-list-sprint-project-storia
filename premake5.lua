workspace "Storia"
   configurations { "Debug", "Release" }
   location "build"
 
project "Storia"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
 
   files { "main.cpp", "src/**.cpp", "include/**.h", "include/**.hpp", "assets/**" }
   includedirs { "include", "lib/json/include", "lib/crypto" }
   links { "crypto" }
 
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
 
   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

project "crypto"
      kind "StaticLib"
      language "C++"
      targetdir "bin/%{cfg.buildcfg}"
    
      files { "lib/crypto/**.cpp", "lib/crypto/**.h" }
      includedirs { "include" }
    
      filter "configurations:Debug"
         defines { "DEBUG" }
         symbols "On"
    
      filter "configurations:Release"
         defines { "NDEBUG" }
         optimize "On" 
 
project "test"
   kind "SharedLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
 
   files { "test/**.cpp", "test/**.h", "test/**.hpp" }
   includedirs { "include", "lib/json/include", "lib/crypto" }
   links { "crypto" }
 
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
 
   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
 
   postbuildcommands {
      "{COPY} %{cfg.buildtarget.relpath} ../bin"
   }
 