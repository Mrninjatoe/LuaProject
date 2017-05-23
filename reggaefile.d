import reggae;

enum CompileCommand {
	Compile = "g++ -c -std=c++17 -O0 -D_DEBUG -ggdb -Wall -fdiagnostics-color=always -fopenmp -Iinclude $in -o $out",
	Link = "g++ -std=c++17 -O0 -ggdb -Wall -fdiagnostics-color=always -fopenmp -lm -ldl -lSDL2 -lSDL2_image -llua -lGL $in -o $out",

	CompileEditor = "g++ -c -std=c++17 -O0 -D_DEBUG -ggdb -fdiagnostics-color=always -fopenmp $in -o $out",
	LinkEditor = "g++ -std=c++17 -O0 -ggdb-fdiagnostics-color=always -fopenmp -lm -ldl -lSDL2 -lSDL2_image -lSDL2_ttf -lGL $in -o $out"
}

Target[] MakeObjects(string src)(CompileCommand compile) {
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
		objs ~= Target(f ~ ".o", compile, [Target(f)], head);
	}

	return objs;
}

Build myBuild() {
	auto trigonoverthrow = Target("luaproject", CompileCommand.Link, MakeObjects!("src/")(CompileCommand.Compile));
	auto editor = Target("luaeditor", CompileCommand.LinkEditor, MakeObjects!("editor/")(CompileCommand.CompileEditor));

	return Build(trigonoverthrow, editor);
}
