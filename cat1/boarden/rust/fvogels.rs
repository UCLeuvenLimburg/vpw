use std::io::{self};


fn next() -> i32
{
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    let trimmed = line.trim_right();

    return trimmed.parse::<i32>().unwrap();
}

fn main()
{
    let n_cases = next();

    for index in 1..n_cases+1
    {
        let n = next();
        let mut count = 1;
        let mut last = std::i32::MAX;

        for _ in 0..n
        {
            let k = next();

            if k > last
            {
                count += 1;
            }

            last = k
        }
        
        println!("{} {}", index, count);
    }
}
