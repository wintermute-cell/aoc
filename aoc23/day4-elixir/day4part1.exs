defmodule Part1 do
  def read_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  def parse_line(str) do
    regex = ~r/Card\s+(\d+): ([\d ]+)\| ([\d ]+)/

    case Regex.run(regex, str) do
      [_, _, first_list_str, second_list_str] ->
        toi = fn v -> (v |> String.split |> Enum.map(&String.to_integer/1)) end
        {"", toi.(first_list_str), toi.(second_list_str)}
      _ ->
        :error
    end
  end

  def solve(input_string) do
    Enum.reduce(input_string |> String.split("\n"), 0, fn card_line, acc ->
      case parse_line(card_line) do
        {id, l, r} -> 
          winning_nums = MapSet.intersection(MapSet.new(l), MapSet.new(r)) |> MapSet.to_list |> length
          Kernel.trunc(2**(winning_nums-1)) + acc
         _ -> acc
      end
      
    end)
  end
  
end

Part1.read_file("input.txt") |> Part1.solve |> IO.inspect
