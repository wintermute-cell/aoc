defmodule Day8 do
  def read_file(path) do
    {:ok, contents} = File.read(path)
    contents
  end

  def solve(input) do
    input
    |> String.split("\n", trim: true)
    |> Enum.map(fn line ->
      line |> String.split() |> Enum.map(&String.to_integer/1)
    end)
    |> Enum.map(fn line -> analyze(line) end)
    |> Enum.sum()
  end

  def analyze(sequence) do
    case Enum.uniq(sequence) do
      [0] ->
        0

      _ ->
        step =
          sequence
          |> Enum.chunk_every(2, 1, :discard)
          |> Enum.map(fn [l, r] -> r - l end)
          |> analyze()

        hd(sequence) - step
    end
  end
end

Day8.read_file("input.txt") |> Day8.solve() |> IO.inspect(charlists: :as_lists)
