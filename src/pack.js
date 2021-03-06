import packer from './packer';

let packFn;

const loading = packer({
  noInitialRun: true,
  locateFile() {
    return 'packer.wasm';
  }
}).then((module) => {
  packFn = module.cwrap('pack', 'number', ['number', 'array']);
});

export class Box {
  constructor(width, height, depth) {
    this.width = width;
    this.height = height;
    this.depth = depth;
  }
}

/**
 * @param {Box[]} boxes
 * @return {Promise<Number>}
 */
export async function pack (boxes) {
  if (!packFn) {
    await loading;
  }

  const flattened = boxes
    .map(({width, height, depth}) => [width, height, depth])
    .flat();
  return packFn(flattened.length, flattened);
}