workspace "Storia"
   configurations { "Debug", "Release" }
   location "build"

project "Storia"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "main.cpp", "src/**.cpp", "include/**.h", "include/**.hpp", "assets/**" }
   includedirs { "include" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
