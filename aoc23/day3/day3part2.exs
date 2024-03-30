defmodule Day3.Part2 do

  def read_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  def solve(input) do
    lines = input |> String.split("\n")
    symbol_lines = lines |> Enum.map(fn line -> 
      Regex.scan(~r/\*/, line, return: :index) 
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

    z = Enum.with_index(symbol_lines)
      |> Enum.map(fn {symbol_line, idx} ->
        case idx-1 do
          -1 -> 
            %{nl: Enum.slice(number_lines, 0, 2), sl: symbol_line}
          _ -> 
            %{nl: Enum.slice(number_lines, idx-1, 3), sl: symbol_line}
        end
      end)

    z = z |> Enum.reverse |> tl() |> Enum.reverse # strip empty line



    Enum.reduce(z, 0, fn line, acc -> # for every number line
      symbol_indices = Enum.to_list(line.sl) |> List.flatten
      Enum.reduce(symbol_indices, 0, fn symbol_index, line_acc -> # for every symbol

        # get adjacent numbers
        numbers = line.nl |> List.flatten |> IO.inspect
        adjacent_nums = Enum.filter(numbers, fn {range_start, range_end, _val} -> # for every number
          range = range_start..range_end
            symbol_index in range
        end)


        cond do
          # if two adjacent, return acc + adjacent1 + adjacent2
          adjacent_nums |> length  == 2 ->
            line_acc + Enum.reduce(adjacent_nums, 1, fn num, adj_acc -> elem(num, 2) * adj_acc end)
          # otherwise, dont add anything
          true ->
            line_acc
        end

      end) + acc

    end) |> IO.inspect

    #Enum.reduce(z, 0, fn line, acc -> # for every number line
    #  acc + Enum.reduce(line.nl, 0, fn {range_start, range_end, val}, line_acc -> # for every number
    #    range = range_start..range_end
    #    sl_positions = Enum.to_list(line.sl) |> List.flatten

    #    cond do
    #      Enum.any?(sl_positions, fn num -> num in range end) ->
    #        line_acc + val
    #      true ->
    #        line_acc
    #    end
    #  end)
    #end) |> IO.inspect

  end

end

Day3.Part2.read_file("input.txt") |> Day3.Part2.solve
