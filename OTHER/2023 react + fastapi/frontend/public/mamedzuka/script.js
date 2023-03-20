//before work write in terminal "python -m http.server 8000"
console.log("canvas script running")

function drawImage(context, arr_images, counter_image) {
    context.drawImage(arr_images[counter_image], 0, 0);
    console.log(`image #${counter_image} drawn`);
    if (counter_image < 19) {
        counter_image++;
    } else {
        counter_image = 0;
    }   
}

async function main() {
    let timer;
    let arr_images;
    let next_image;
    let previous_image;

    let counter_image = 0;

    const canvas = document.querySelector("canvas");
    const context = canvas.getContext("2d");   
    const button_clear = setButton("button-clear");
    const button_next = setButton("button-next");
    const button_previous = setButton("button-previous");
    const button_play = setButton("button-play");
    const button_stop = setButton("button-stop");
    const button_load_images = setButton("button-load-images");
    
    setCanvas(canvas, width=1920, height=1080);
    
    button_load_images.onclick = async function() {
        arr_images =  [];
        for (let i = 0; i < 20; i++) {
            if (i < 10) {
                arr_images.push(await loadImage(`images/frame_0${i}_delay-0.01s.jpg`));
            } else {
                arr_images.push(await loadImage(`images/frame_${i}_delay-0.01s.jpg`));
            }
        }
        alert("images loaded")
    }

    button_clear.onclick = function() {
        canvas.width = canvas.width;
        console.log("canvas cleared");
    }

    button_play.onclick = function() {
        timer = setInterval(function () {
            context.drawImage(arr_images[counter_image], 0, 0);
            console.log(`image #${counter_image} drawn`);
            if (counter_image < 19) {
                counter_image++;
            } else {
                counter_image = 0;
            }   
            next_image = true;
        }, 250)   
    }

    button_stop.onclick = function() {
        clearInterval(timer)
    }

    button_next.onclick = function() {
        if (previous_image) {
            counter_image++;
            previous_image = false;
        }
        context.drawImage(arr_images[counter_image], 0, 0);
        console.log(`next image (#${counter_image}) drawn`);
        if (counter_image < 19) {
            counter_image++;
        } else {
            counter_image = 0;
        }   
        next_image = true;
    }

    button_previous.onclick = function() {
        if (counter_image > 0) {
            if (next_image) {
                counter_image -= 2;
            } else {
                counter_image--;
            }
            next_image = false;
        } else {
            counter_image = 19;
        }   
        previous_image = true;
        context.drawImage(arr_images[counter_image], 0, 0);
        console.log(`previous image (#${counter_image}) drawn`);
    }
    
    // const button = document.getElementById(button_id)
    // button.onclick = function () {
    //     fun_onclick(fun_arg)
    // }
    // 
    // buttonClick("button-test-draw", testDraw, context);
    // buttonClick("button-clear", clearCanvas, canvas);
    // buttonClick("button-clear", clearCanvas, canvas);
    // button_next.onclick = async function() {
    //     const image = await loadImage(`images/frame_0${number_image}_delay-0.01s.jpg`);
    //     // drawCanvasImage(context)
    //     context.drawImage(image, 0, 0)
    //     if (number_image < 9) {
    //         number_image++;
    //     } else {
    //         number_image = 0;
    //     }
    // }

}

function loadImage(src) {
	return new Promise((resolve) => {
		const image = new Image();
		image.src = src;
		image.onload = () => resolve(image);
	});
}

// async function drawCanvasImage(context, src) {
    

//     context.drawImage(image, 0, 0)
// }

function setButton(button_id) {
    return document.getElementById(button_id)
}

function setCanvas(canvas, width = 500, height = 500) {  
    canvas.width = width;
    canvas.height = height;
    console.log("canvas setted");
}

function clearCanvas(canvas) {
    canvas.width = canvas.width;
    console.log("canvas cleared");
}

main()