import { NativeModules } from 'react-native';

export function multiply(a: number, b: number): Promise<number> {
  return NativeModules.SampleLib.multiply(a, b);
}
