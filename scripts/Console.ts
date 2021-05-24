export namespace Console {
    let encoder = new TextEncoder();
    let newLine = encoder.encode(Deno.build.os == "windows" ? "\r\n" : "\n");

    export function write(str: string) {
        Deno.stdout.write(encoder.encode(str));
    }

    export function writeLine(str: string) {
        write(str);
        Deno.stdout.write(newLine);
    }
}