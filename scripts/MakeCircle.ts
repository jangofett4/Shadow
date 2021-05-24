import { Console } from "./Console.ts";

if (Deno.args.length < 1) {
    Console.writeLine("Usage: MakeCircle number-of-corners");
    Deno.exit(1);
}

function deg2rad(deg : number) : number {
    return deg * Math.PI / 180;
}

let corners = Number.parseInt(Deno.args[0]);
Console.write("vec2(0,0),"); // origin point, used for triangle fan
for (let i = corners - 1; i > 0; i--) 
    Console.write(`vec2(${ Math.cos(deg2rad(i)) },${ Math.sin(deg2rad(i)) }),`);
Console.write(`vec2(${ Math.cos(deg2rad(0)) },${ Math.sin(deg2rad(0)) })`);