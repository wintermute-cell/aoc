defmodule Day7 do
  def solve(path) do
    {:ok, content} = File.read(path)
    content
    |> String.split("\n", trim: true)
    |> Enum.map(fn line -> line |> String.split end)
    |> Enum.map(fn hand_pair -> {hand_with_type(hd(hand_pair)), hd(tl(hand_pair)) |> String.to_integer} end)
    |> Enum.group_by(fn {{_, type}, _} -> type end)
    |> Enum.map(fn type_set ->
      type_set |> elem(1) |> Enum.sort_by(fn {{letters, _}, _} -> letters end)
    end)
    |> Enum.concat()
    |> Enum.map(fn {{letters, type}, bid} -> bid end) |> Enum.with_index
    |> Enum.map(fn {bid, idx} -> bid*(idx+1) end)
    |> Enum.sum
  end

  @substitution_map %{
    "A" => "E", "K" => "D", "Q" => "C", "J" => "B", "T" => "A"
  }

  @spec substitute_chars(list(String.t)) :: list(String.t)
  defp substitute_chars(chars) do
    chars |> Enum.map(fn char ->
      Map.get(@substitution_map, char, char)
    end)
  end

  @spec hand_with_type(String.t) :: {String.t, integer}
  defp hand_with_type(hand) do
    counts = hand |> String.graphemes |> Enum.frequencies |> Enum.into([])
    sorted_counts = Enum.sort_by(counts, fn {_, count} -> -count end)
    hand = hand |> String.graphemes |> substitute_chars()

    case sorted_counts do
      [{_, 5}] -> 
        {hand, 6}
      [{_, 4}, _] -> 
        {hand, 5}
      [{_, 3}, {_, 2}] -> 
        {hand, 4}
      [{_, 3}, _, _] -> 
        {hand, 3}
      [{_, 2}, {_, 2}, _] -> 
        {hand, 2}
      [{_, 2}, _, _, _] -> 
        {hand, 1}
      _ -> 
        {hand, 0}
    end
  end

end

Day7.solve("input.txt") |> IO.inspect(charlists: :as_lists)