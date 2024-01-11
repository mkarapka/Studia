extern crate nom;
use std::env;
use std::fs::read_to_string;
use nom::{
    branch::alt,
    bytes::complete::tag,
    character::complete::space0,
    multi::separated_list0,
    sequence::{delimited, tuple},
    IResult, combinator::{map, value},
};

#[derive(Debug, Clone)]
enum Command {
    ClearScreen,
    SetTurtle(i32),
    PenUp,
    Right(i32),
    Forward(i32),
    Left(i32),
    PenDown,
    Repeat(i32, Vec<Command>),
}

fn parse_number(input: &str) -> IResult<&str, i32> {
    use nom::character::complete::digit1;
    use nom::combinator::map_res;
    map_res(digit1, |digit_str: &str| digit_str.parse::<i32>())(input)
}

fn parse_command(input: &str) -> IResult<&str, Command> {
    alt((

        value(Command::ClearScreen, tag("clearscreen")),
        value(Command::PenUp, tag("penup")),
        value(Command::PenDown, tag("pendown")),
        map(
            tuple((
                tag("repeat"),
                space0,
                parse_number,
                space0,
                delimited(tag("["), parse_commands, tag("]")),
            )),
            |(_, _, n, _, cmds)| Command::Repeat(n, cmds),
        ),
        map(tuple((tag("setturtle"), space0, parse_number)), |(_, _, n)| {
            Command::SetTurtle(n)
        }),
        map(tuple((alt((tag("right"), tag("rt"))), space0, parse_number)), |(_, _, n)| {
            Command::Right(n)
        }),
        map(tuple((alt((tag("forward"), tag("fd"))), space0, parse_number)), |(_, _, n)| {
            Command::Forward(n)
        }),
        map(tuple((alt((tag("left"), tag("lt"))), space0, parse_number)), |(_, _, n)| {
            Command::Left(n)
        }),
        
    ))(input)
}
fn parse_commands(input: &str) -> IResult<&str, Vec<Command>> {
    separated_list0(space0, parse_command)(input)
}
use std::fs;

fn main() {
    let filename = "/home/mikol/Projects/3_sem/Rust-2023/L7/src/tests/test.logo"; // replace with your file name
    let content = fs::read_to_string(filename);
    
    match content {
        Ok(data) => {
            let result = parse_commands(&data);
            println!("{:?}", result);
        },
        Err(error) => {
            println!("Error reading file: {:?}", error);
        }
    }
}
