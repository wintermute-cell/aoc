defmodule Day3.Part1 do

  def read_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  def solve(input) do
    lines = input |> String.split("\n")
    symbol_lines = lines |> Enum.map(fn line -> 
      Regex.scan(~r/[^0-9\.]/, line, return: :index) 
        |> Enum.map(fn line_matches ->
          line_matches 
          |> Enum.map(fn match ->
            match |> elem(0)
          end)
        end)
    end)

    number_lines = lines |> Enum.map(fn line ->
      Regex.scan(~r/[0-9]+/, line, return: :index) 
        |> Enum.map(fn line_matches ->
          line_matches 
          |> Enum.map(fn match ->
            start = elem(match, 0)
            ending = start + elem(match, 1)
            {start-1, ending, String.slice(line, start, elem(match, 1)) |> String.to_integer}
          end) |> Enum.at(0) 
        end)
    end)


    # for each number i, take three lines of symbols (i-1, i, i+1)
    # then for each line of sybols, for each symbol, check if the symbol is in the range of the number.
    # if yes, count the number

    z = Enum.with_index(number_lines)
      |> Enum.map(fn {number_line, idx} ->
        case idx-1 do
          -1 -> 
            %{nl: number_line, sl: Enum.slice(symbol_lines, 0, 2)}
          _ -> 
            %{nl: number_line, sl: Enum.slice(symbol_lines, idx-1, 3)}
        end
      end)

    z = z |> Enum.reverse |> tl() |> Enum.reverse


    Enum.reduce(z, 0, fn line, acc -> # for every number line
      acc + Enum.reduce(line.nl, 0, fn {range_start, range_end, val}, line_acc -> # for every number
        range = range_start..range_end
        sl_positions = Enum.to_list(line.sl) |> List.flatten

        cond do
          Enum.any?(sl_positions, fn num -> num in range end) ->
            line_acc + val
          true ->
            line_acc
        end
      end)
    end) |> IO.inspect

  end

end

Day3.Part1.read_file("input.txt") |> Day3.Part1.solve
