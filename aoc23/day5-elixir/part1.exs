defmodule Part1 do
  def read_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  def solve(input) do
    lines = input |> String.split("\n")
    seeds = hd(lines) |> String.split |> tl |> Enum.map(&String.to_integer/1)
    maps = tl(lines)


    transforms = maps
    |> Enum.chunk_by(fn line -> line == "" end)
    |> Enum.filter(fn line -> hd(line) != "" end)
    |> Enum.map(fn [name | number_lines] ->  # for each map set
      Enum.map(number_lines, fn line -> 
        [dest, src, rng] = line |> String.split |> Enum.map(&String.to_integer/1)
        offset = dest - src # amount to shift by
        %{rngl: src, rngr: src+rng-1, offs: offset, id: name}
      end)
    end)

     last_stage = transforms |> Enum.reduce(seeds, fn map_set, seeds_acc ->
      seeds_acc |> Enum.map(fn seed ->
        map_set |> Enum.reduce(seed, fn map_line, seed_acc ->
          case seed do
             x when x in map_line.rngl..map_line.rngr ->
              x + map_line.offs
             _ -> seed_acc
          end
        end)
      end)
    end)

    last_stage |> Enum.min

  end
end

# input
# destination source range

Part1.read_file("input.txt") |> Part1.solve() |> IO.inspect(charlists: :as_lists)
