
use std::{fs, collections::HashSet};
use regex::Regex;

fn parse_file(contents: &str) -> Vec<(&str, Vec<u32>, Vec<u32>)> {
    let re = Regex::new(r"Card\s+(\d+): ([\d ]+) \| ([\d ]+)").unwrap();
    let mut lines: Vec<(&str, Vec<u32>, Vec<u32>)> = vec![];
    for (_, [id, l, r]) in re.captures_iter(&contents[..]).map(|c| c.extract()) {
        let left_nums = l.to_string().split_whitespace()
            .filter_map(|num| num.parse::<u32>().ok())
            .collect::<Vec<u32>>();

        let right_nums = r.to_string().split_whitespace()
            .filter_map(|num| num.parse::<u32>().ok())
            .collect::<Vec<u32>>();

        lines.push((id, left_nums, right_nums));
    }
    return lines;
}

fn main() {
    // gameplan
    // 1.for each line/card, regex the numbers into two lists
    // find the intersection
    // count 2**(intersecting_numbers-1) for each card

    let contents = fs::read_to_string("input.txt")
        .expect("Could not open input file!");
    let parsed_cards = parse_file(&*contents);

    use std::time::Instant;
    let now = Instant::now();


    let mut sum: i32 = 0;
    for card in parsed_cards {
        let (_, left, right) = card;
        let lset = HashSet::<u32>::from_iter(left);
        let rset = HashSet::<u32>::from_iter(right);
        let winning_nums = u32::try_from(lset.intersection(&rset).count()).unwrap();
        if winning_nums > 0 {
            sum += i32::pow(2 as i32, winning_nums-1);
        } else {
            sum += 0;
        }
    }

    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);

    println!("{:?}", sum);
}
