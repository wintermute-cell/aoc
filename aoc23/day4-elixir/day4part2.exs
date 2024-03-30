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
    Enum.reduce(input_string |> String.split("\n"), %{cards: 0, doubles: [0]}, fn card_line, acc ->
      case parse_line(card_line) do
        {id, l, r} -> 
          winning_nums = MapSet.intersection(MapSet.new(l), MapSet.new(r)) |> MapSet.to_list |> length
          %{
            cards: acc.cards+(hd(acc.doubles)+1),
            doubles: add_doubles(tl(acc.doubles), winning_nums, hd(acc.doubles)+1)++[0]}
         _ -> %{cards: acc.cards, doubles: tl(acc.doubles)++[0]}
      end
      
    end)
  end

  def add_doubles(curr_doubles, amount, increment) do
    {l, r} = Enum.split(curr_doubles, amount)
    incremented = Enum.map(l, &(&1 + increment))
    appended = List.duplicate(increment, max(amount - length(l), 0))
    incremented ++ r ++ appended
  end
  
end

:timer.tc(fn  -> Part1.read_file("input.txt") |> Part1.solve |> IO.inspect end, []) |> IO.inspect()
