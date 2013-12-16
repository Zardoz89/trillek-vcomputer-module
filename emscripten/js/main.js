
  var vm = new Module.VirtualComputer(128*1024);
  var cda = new Module.CDA(0,0);
  var key = new Module.GKeyboard(0,2);
  vm.AddKeyboard(3, key);
  vm.AddCDA(5, cda);

  // Generate a Buffer that bridges ToRGBATexture and WebGL texture 
  // Get data byte size, allocate memory on Emscripten heap, and get pointer
  var nBytes = 320*240*4;
  var texturePtr = Module._malloc(nBytes);

  // Creates a Type Array using this emscripten heap memory block
  var textureHeap = new Uint8Array(Module.HEAPU8.buffer, texturePtr, nBytes);
  for (var i=0; i < 320*240*4; i = i + 4) // And fill it of black
    textureHeap.set([0, 0 ,0 ,0], i);


  // WebGL stuff
  var gl;
  // Inits WebGL stuff
  function initGL(canvas) {
    try {
      gl = canvas.getContext("experimental-webgl");
      gl.viewportWidth = canvas.width;
      gl.viewportHeight = canvas.height;
    } catch (e) {
    }

    if (!gl) {
      alert("Could not initialise WebGL, sorry :-(");
    }
  }

  function getShader(gl, id) {
      var shaderScript = document.getElementById(id);
      if (!shaderScript) {
          return null;
      }

      var str = "";
      var k = shaderScript.firstChild;
      while (k) {
          if (k.nodeType == 3) {
              str += k.textContent;
          }
          k = k.nextSibling;
      }

      var shader;
      if (shaderScript.type == "x-shader/x-fragment") {
          shader = gl.createShader(gl.FRAGMENT_SHADER);
      } else if (shaderScript.type == "x-shader/x-vertex") {
          shader = gl.createShader(gl.VERTEX_SHADER);
      } else {
          return null;
      }

      gl.shaderSource(shader, str);
      gl.compileShader(shader);

      if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
          alert(gl.getShaderInfoLog(shader));
          return null;
      }

      return shader;
  }


  var shaderProgram;

  // Initialize and load the shaders
  function initShaders() {
      var fragmentShader = getShader(gl, "shader-fs");
      var vertexShader = getShader(gl, "shader-vs");

      shaderProgram = gl.createProgram();
      gl.attachShader(shaderProgram, vertexShader);
      gl.attachShader(shaderProgram, fragmentShader);
      gl.linkProgram(shaderProgram);

      if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
          alert("Could not initialise shaders");
      }

      gl.useProgram(shaderProgram);

      shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
      gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

      shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
      gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);

      shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
      shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
      shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, "uSampler");
  }

  /**
   * Updated Texture with CDA last state
   */
  function updateTexture(texture, cda) {
    gl.bindTexture(gl.TEXTURE_2D, texture);
    // Call function and get result
    cda.ToRGBATexture(texture.rawdata.byteOffset);
  
    gl.texSubImage2D(gl.TEXTURE_2D, 0, 
        0, 0 , 320, 240,
        gl.RGBA, gl.UNSIGNED_BYTE, texture.rawdata);
    gl.bindTexture(gl.TEXTURE_2D, null);
    cda.VSync();
  }

  // Sets the texture parameters and load a initial image
  function handleLoadedTexture(texture) {

    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
    // Call function and get result
    cda.ToRGBATexture(texture.rawdata.byteOffset);
  
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 320, 240, 0,
        gl.RGBA, gl.UNSIGNED_BYTE, texture.rawdata);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE); 
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.bindTexture(gl.TEXTURE_2D, null);
  }

  var glTexture;

  // Init the texture
  function initTexture() {
    glTexture = gl.createTexture();
    glTexture.rawdata = textureHeap;
    handleLoadedTexture(glTexture)
  }

  var mvMatrix = mat4.create();
  var mvMatrixStack = [];
  var pMatrix = mat4.create();

  function mvPushMatrix() {
      var copy = mat4.create();
      mat4.set(mvMatrix, copy);
      mvMatrixStack.push(copy);
  }

  function mvPopMatrix() {
      if (mvMatrixStack.length == 0) {
          throw "Invalid popMatrix!";
      }
      mvMatrix = mvMatrixStack.pop();
  }


  function setMatrixUniforms() {
      gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
      gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
  }

  var VPBuffer;
  var VTexCoordBuffer;
  var VIndexBuffer;

  // Init Vertex Buffers
  function initBuffers() {
      VPBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, VPBuffer);
      vertices = [
          // Front face
          -3.2, -2.4,  0.0,
           3.2, -2.4,  0.0,
           3.2,  2.4,  0.0,
          -3.2,  2.4,  0.0,
      ];
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
      VPBuffer.itemSize = 3;
      VPBuffer.numItems = 4;

      VTexCoordBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ARRAY_BUFFER, VTexCoordBuffer);
      var textureCoords = [
        // Front face
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
      ];
      gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
      VTexCoordBuffer.itemSize = 2;
      VTexCoordBuffer.numItems = 4;

      VIndexBuffer = gl.createBuffer();
      gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, VIndexBuffer);
      var vertexIndices = [
          0, 1, 2,      0, 2, 3,    // Front face
      ];
      gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(vertexIndices), gl.STATIC_DRAW);
      VIndexBuffer.itemSize = 1;
      VIndexBuffer.numItems = 6;
  }

  // Update WebGL scene
  function drawScene() {
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, pMatrix);

    mat4.identity(mvMatrix);

    mat4.translate(mvMatrix, [0.0, 0.0, -6.0]);

    gl.bindBuffer(gl.ARRAY_BUFFER, VPBuffer);
    gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, VPBuffer.itemSize, gl.FLOAT, false, 0, 0);

    gl.bindBuffer(gl.ARRAY_BUFFER, VTexCoordBuffer);
    gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, VTexCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);


    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, glTexture);
    gl.uniform1i(shaderProgram.samplerUniform, 0);
    
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, VIndexBuffer);
    setMatrixUniforms();
    gl.drawElements(gl.TRIANGLES, VIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
  }

  // Use to control timings
  var lastTime = 0;
  var updTexTime = 0;
  var updSpeed = 0;

  var cycles = 1350; // How many cycles are being executed in a bath
  var tms = (cycles / 100000.0) * 1000; // Time in ms that should be running

  var loop = false;
  function tick() { // This is executed every tick
    if (loop)
      requestAnimFrame(tick);

    var timeNow = new Date().getTime(); 
    if (lastTime != 0) {
      var elapsed = timeNow - lastTime;
      //trace("PC:" + vm.CPUState().pc);
      //var ticks = vm.Step(elapsed);
      vm.Tick(cycles, elapsed);

      updTexTime += elapsed;
      if (updTexTime >= 40) { // 25 FPS in milliseconds
        updateTexture(glTexture, cda);
        updTexTime -= 40;
      }

      updSpeed += elapsed;
      if (updSpeed >= 2000) {
        var speed = 100.0 * (tms / elapsed)
        trace("Speed: " + speed);
        updSpeed -= 2000;
      }
    }

    drawScene();
    
    lastTime = timeNow;
  }

  var filePtr;
  var fileHeap;

  var canvas = document.getElementById('canvas1');
  initGL(canvas);
  initShaders();
  initBuffers();
  initTexture();

  gl.clearColor(0.2, 0.2, 0.2, 1.0);
  gl.enable(gl.DEPTH_TEST);

  document.onkeydown = function (evt) {
    var k = evt.keyCode;
    if (loop) {
      evt.preventDefault();
      key.PushKeyEvent (true, k);
    }
    return false;
  };
  
document.onkeyup = function (evt) {
    var k = evt.keyCode;
    if (loop) {
      evt.preventDefault();
      key.PushKeyEvent (false, k);
    }
    return false;
  };


  var selector = document.getElementById('romfile');
  selector.addEventListener('change', function(evt){
    loop = false;
    
    // Check for the various File API support.
    if (window.File && window.FileReader && window.FileList && window.Blob) {
      var files = evt.target.files; // FileList object
      var file = files[0];
      var reader = new FileReader();

      reader.onload = (function(theFile){
        return function(e) {
          if (typeof (fileHeap) != 'undefined')
            Module._free(fileHeap.byteOffset); // Free the Heap

          var bytes = theFile.size;
          if (bytes > 64*1024)
            bytes = 64*1024;

          trace("Loaded ROM file : " + theFile.name + " Size of : " + bytes);

          // Get data byte size, allocate memory on Emscripten heap, and get pointer
          filePtr = Module._malloc(bytes); 
          // Creates a Type Array using this emscripten heap memory block
          fileHeap = new Uint8Array(Module.HEAPU8.buffer, filePtr, bytes);
          var tmp = new Uint8Array(reader.result, 0, bytes);
          fileHeap.set(tmp);
          vm.WriteROM(fileHeap.byteOffset, bytes);

        };
      })(file);
      
      reader.readAsArrayBuffer(file)
      loop = true;
      tick();

    } else {
      alert('The File APIs are not fully supported in this browser.');
    }
  }, false);

 // Free memory
 // Module._free(textureHeap.byteOffset);
