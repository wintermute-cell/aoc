defmodule Slide do
  defstruct [:low_rngl, :low_rngr, :high_rngl, :high_rngr, :layer, :reaches]
end

defmodule Part1 do
  def read_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  def solve(input) do
    # parse input
    lines = input |> String.split("\n")
    seeds = hd(lines) |> String.split |> tl |> Enum.map(&String.to_integer/1) |> Enum.chunk_every(2)
    slide_layers = tl(lines)
      |> Enum.chunk_by(fn line -> line == "" end)
      |> Enum.filter(fn line -> hd(line) != "" end)
      |> Enum.map(fn line -> tl(line) end)
      |> Enum.map(fn x_to_x -> 
        x_to_x |> Enum.map(fn slide ->
          slide
            |> String.split
            |> Enum.map(fn num -> num |> String.to_integer end)
        end)
      |> Enum.sort_by(fn slide -> hd(tl(slide)) end)
      end)
  end

  # throw a seed at a slide, and get back one or more intervals, based on how the seed falls
  defp throw_at_slide([seed_left, seed_length], [slide_dest, slide_src, slide_length]) do
  end
end

# input
# destination source range

Part1.read_file("input.txt") |> Part1.solve()  |> IO.inspect(charlists: :as_lists)
