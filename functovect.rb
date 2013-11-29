#!/bin/ruby
def handle_piece(piece, amplitudes, frequencies)
	piece.strip!
	values = piece.scan(/([0-9]*\.[0-9]+)f?\*sin\(phase\*([0-9]*\.[0-9]+)/).flatten
	raise "Invalid sin piece: #{piece}\nGot #{values})" unless values.size == 2
	amplitudes.push(values[0])
	frequencies.push(values[1])
	return values
end

amplitudes = []
frequencies = []
until $stdin.eof? do
	line = readline
	pieces = line.split("+")
	pieces.each{|p| handle_piece(p, amplitudes, frequencies)}
end

puts <<END
amplitudes = [ #{amplitudes.join("; ") }];
frequencies = [ #{frequencies.join("; ")} ];
END
