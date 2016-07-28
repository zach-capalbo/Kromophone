#!/usr/bin/env ruby
require 'fileutils'

BUILD_DIR = "/home/zach/src/cpp/builds/build-Kromophone-Desktop_Qt_5_7_0_GCC_64bit-Release"

def libraries_for(file)
  libs = `ldd #{file}`.each_line.map{|i| i.split }.reject{|i| i.size < 4}.map{|i| [i.first, File.realpath(i[2])]}
end

def make_links(libs)
  Dir.chdir(BUILD_DIR) do
    libs.each do |name, path|
      begin
      FileUtils.rm name if File.exist?(name)
      FileUtils.cp path, name
      rescue
        puts "#{path}, #{name}"
        puts $!
      end
    end.map {|name, path| ["#{BUILD_DIR}/#{name}"]}.flatten
  end
end

if __FILE__ == $0 then
  libs = [
    "#{BUILD_DIR}/Kromophone",
    "/opt/Qt/5.7/gcc_64/plugins/platforms/libqxcb.so",
    "/opt/Qt/5.7/gcc_64/lib/libQt5XcbQpa.so.5",
    "/opt/Qt/5.7/gcc_64/plugins/xcbglintegrations/libqxcb-glx-integration.so"
  ].map{|l| libraries_for(l)}.reduce{|a,b| a | b}.reject do |name,path|
    [
      "libstdc++",
      "libgcc_s",
      "libGL"
    ].any?{|p| name.include?(p)}
  end
files = make_links(libs).sort.select{|f| File.exist?(f)}
File.write("/tmp/f.txt", files.map{|f| %|                        <distributionFile><origin>#{f}</origin></distributionFile>|}.join("\n"))
system("cat /tmp/f.txt | xclip -i")
end
