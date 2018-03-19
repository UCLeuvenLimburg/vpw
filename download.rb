require 'open-uri'
require 'pathname'
require 'fileutils'



def download_problem(subdirectory, url)
  if String === subdirectory
    subdirectory = Pathname.new subdirectory
  end

  subdirectory.mkpath
  
  
  files = open(url) do |stream|
    data = stream.read

    data.scan(%r{<a href="(.*?\.(pdf|invoer|uitvoer))">}).map do |x, y|
      x
    end
  end

  files.each do |file|
    source = "#{url}#{file}"
    target = subdirectory + file

    puts "#{source} -> #{target}"
    open(source) do |source|
      open(target, 'wb') do |target|
        target.write(source.read)
      end
    end
  end
end


def download_problem_names(url)
  puts "Getting problem names at #{url}"
  open(url) do |stream|
    data = stream.read
    
    data.scan(%r{href="(.*?)/">\1}).flatten
  end
end

def download(base_url)
  (1..4).each do |n|
    url = "#{base_url}cat#{n}/"
    names = download_problem_names url

    names.each do |name|
      subdirectory = "cat#{n}/#{name}"
      problem_url = "#{url}#{name}/"
      
      download_problem(subdirectory, problem_url)
    end
  end
end


download('https://www.vlaamseprogrammeerwedstrijd.be/current/opgaven/2018/')
