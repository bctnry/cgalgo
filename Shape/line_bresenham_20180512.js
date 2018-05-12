
"use strict";



const UP = 1;
const DOWN = 0;

let firstX = 0, firstY = 0, secondX = 0, secondY = 0;
// this is for controlling when to actually draw the line
// because p5.js flush automatically.
let drawingLock = true;

function setup() {
    createCanvas(640, 480);
}

function draw() {
    background(0);
    stroke(255);
    fill(0);
    if(drawingLock);
    else {
        bresenham();
    }
}

function mouseMoved() {
    firstX = mouseX;
    firstY = mouseY;
}

function mouseDragged() {
    secondX = mouseX;
    secondY = mouseY;
    drawingLock = false;
    bresenham();
}

function mouseReleased() {
    drawingLock = true;
}

function bresenham() {
    let x1 = firstX, y1 = firstY, x2 = secondX, y2 = secondY;
    let dx = x2 - x1, dy = y2 - y1;
    let x = 0, y = 0, e = 0;

    if(Math.abs(dy) < Math.abs(dx)) {
        // here, |k| <= 1.
        // we draw from left to right.
        // if x1 is at the right of x2 then swap points.
        if(x1 > x2) {
            let temp = x2; x2 = x1; x1 = temp;
            temp = y2; y2 = y1; y1 = temp;
            dx = -dx; dy = -dy;
        }
        /* downwards: k < 0, e = 0.5, e += k,
           if e <= 0 then y--; e += 1 (reset to 0.5);
           else y same;
           upwards: k > 0, e = -0.5, e += k,
           if e >= 0 then y++; e -= 1 (reset to -0.5);
           else y same;
           here, e is actually 2edx --> dx,
           and 1 is actually 2dx.
        */
        let updown = dy > 0? UP : DOWN;
        e = (updown === UP)? -dx : dx;
        x = x1; y = y1;
        for(let i = 0; i <= dx; i++) {
            point(x, y);
            x++; e += 2 * dy;
            if(updown === UP? e >= 0 : e <= 0) {
                y += updown === UP? 1 : -1;
                e += (updown === UP? -1 : 1) * 2 * dx;
            }
        }
    } else {
        // now, |k| > 1. the role of y and x has changed.
        // if y1 is at the top of y2 then swap points.
        if(y1 > y2) {
            let temp = y2; y2 = y1; y1 = temp;
            temp = x2; x2 = x1; x1 = temp;
            dx = -dx; dy = -dy;
        }
        let updown = dx > 0? UP : DOWN;
        /*
          upwards: k > 0, e = -0.5, e += 1/k = dx/dy,
          if e >= 0 then x++, e -= 1 (reset to -0.5)
          downwards: k < 0, e = 0.5, e += 1/k = dx/dy,
          if e <= 0 then x--, e += 1 (reset to 0.5)           
        */
        e = updown === UP? -dy : dy;
        x = x1; y = y1;
        for(let i = 0; i <= dy; i++) {
            point(x, y);
            y++;
            e += 2 * dx;
            if(updown === UP? e >= 0 : e <= 0) {
                x += (updown === UP? 1 : -1);
                e += (updown === UP? -1 : 1) * 2 * dy;
            }
        }
    }
}
