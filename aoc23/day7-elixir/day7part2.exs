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
    |> Enum.map(fn {{_, _}, bid} -> bid end) |> Enum.with_index
    |> Enum.map(fn {bid, idx} -> bid*(idx+1) end)
    |> Enum.sum
  end

  @substitution_map %{
    "A" => "E", "K" => "D", "Q" => "C", "J" => "0", "T" => "A"
  }

  @spec substitute_chars(list(String.t)) :: list(String.t)
  defp substitute_chars(chars) do
    chars |> Enum.map(fn char ->
      Map.get(@substitution_map, char, char)
    end)
  end

  @spec resolve_jokers(list(String.t), list({String.t, integer})) :: list(String.t)
  defp resolve_jokers(chars, sorted_counts) do
    chars |> Enum.map(fn char ->
      case char do
        "J" ->
          # as jester, pick most occuring char that is not J, and mimic it
          most_freq_char = sorted_counts |> Enum.filter(fn {char, _} -> char != "J" end)
          case most_freq_char do
            [] -> "E" # if there is no other char besides J, pick best one
            x -> hd(x) |> elem(0) # otherwise, pick most frequent
          end
        x ->
          # otherwise, just pass the value on
          x
      end
    end)
  end

  @spec hand_with_type(String.t) :: {String.t, integer}
  defp hand_with_type(hand) do
    # this could certainly be smarter without calculating the counts for both
    # the normal and the jestered hand 
    counts = hand |> String.graphemes |> Enum.frequencies |> Enum.into([])
    sorted_counts = Enum.sort_by(counts, fn {_, count} -> -count end)
    jester_hand = hand |> String.graphemes |> resolve_jokers(sorted_counts)
    hand = hand |> String.graphemes |> substitute_chars

    # redo the counts based on the jestered hand
    counts = jester_hand |> Enum.frequencies |> Enum.into([])
    sorted_counts = Enum.sort_by(counts, fn {_, count} -> -count end)

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
