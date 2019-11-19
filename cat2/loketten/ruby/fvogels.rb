class Time
    include Comparable

    def initialize(hours, minutes)
        @timestamp = hours * 60 + minutes
    end

    attr_reader :timestamp

    def +(other)
        Time.new(0, @timestamp + other.timestamp)
    end

    def -(other)
        Time.new(0, @timestamp - other.timestamp)
    end

    def <=>(other)
        timestamp <=> other.timestamp
    end

    def hours
        @timestamp / 60
    end

    def minutes
        @timestamp % 60
    end
end

Citizen = Struct.new(:arrival, :duration)

def solve(n_counters, citizens)
    counters = (0...n_counters).map { Time.new(0, 0) }

    served_at, waiting_time = citizens.map do |citizen|
        counter_index = (0...counters.size).min_by { |i| counters[i] }
        served_at = [ counters[counter_index], citizen.arrival ].max
        waiting_time = served_at - citizen.arrival
        counters[counter_index] = served_at + Time.new(0, citizen.duration)
    
        [ served_at, waiting_time ]
    end.transpose

    [ served_at, waiting_time.map(&:timestamp).max ]
end

def main
    n = gets.to_i

    (1..n).each do |index|
        n_counters = gets.to_i
        n_citizens = gets.to_i

        citizens = (1..n_citizens).map do
            h, m = gets.strip.split(/ /).map(&:to_i)
            d = gets.to_i

            Citizen.new(Time.new(h, m), d)
        end

        served_at, max_waiting_time = solve(n_counters, citizens)
        served_at_string = served_at.map { |time| "#{time.hours} #{time.minutes}" }.join(' ')

        puts "#{index} #{served_at_string} #{max_waiting_time}"
    end
end

main