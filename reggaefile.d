import reggae;
// -Wsuggest-override -Wno-error=suggest-override
enum CFLAGS = "-std=c++17 -O0 -D_DEBUG -ggdb -Wall -fdiagnostics-color=always -fopenmp -Iinclude";

enum CompileCommand {
	Compile = "g++ -c " ~ CFLAGS ~ " $in -o $out",
	Link = "g++ -std=c++17 -O0 -ggdb -Wall -fdiagnostics-color=always -fopenmp -lm -ldl -lSDL2 -lSDL2_image -llua -lGL $in -o $out"
}

Target[] MakeObjects(string src)() {
	import std.file : dirEntries, SpanMode;
	import std.process : executeShell;
	import std.algorithm : map;
	import std.array : array, replace, split;
	import std.range : chain;

	Target[] objs;

	foreach (f; chain(dirEntries(src, "*.cpp", SpanMode.breadth), dirEntries(src, "*.c", SpanMode.breadth)).filter!(x => !x.isDir)) {
		auto exec = executeShell("g++ -MM " ~ f);
		if (exec.status) {
			import std.stdio;
			stderr.writeln("Returned: ", exec.status, "\n", exec.output);
			assert(0);
		}

		auto head = exec.output.split(":")[1].replace("\n", " ").split(" ").filter!(s => !s.empty && s != "\\").map!(x => Target(x)).array;
		objs ~= Target(f ~ ".o", CompileCommand.Compile, [Target(f)], head);
	}

	return objs;
}

Build myBuild() {
	auto trigonoverthrow = Target("luaproject", CompileCommand.Link, MakeObjects!"src/");

	return Build(trigonoverthrow);
}
