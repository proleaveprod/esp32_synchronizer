#include "AudioKitHAL.h"


AudioKit kit;


#define WAV_SIZE   2048
uint8_t wav_array8bit[WAV_SIZE]={        // Wav-signal in 8bit array: MSBL LSBL MSBR LSBR
1, 0, 1, 0,
252, 255, 252, 255,
0, 0, 0, 0,
15, 0, 15, 0,
221, 255, 221, 255,
35, 0, 35, 0,
255, 255, 255, 255,
193, 255, 193, 255,
113, 0, 113, 0,
156, 255, 156, 255,
2, 0, 2, 0,
139, 0, 139, 0,
20, 255, 20, 255,
197, 0, 197, 0,
247, 255, 247, 255,
11, 255, 11, 255,
146, 1, 146, 1,
180, 254, 180, 254,
22, 0, 22, 0,
117, 1, 117, 1,
156, 253, 156, 253,
246, 1, 246, 1,
207, 255, 207, 255,
245, 253, 245, 253,
95, 3, 95, 3,
52, 253, 52, 253,
92, 0, 92, 0,
174, 2, 174, 2,
125, 251, 125, 251,
204, 3, 204, 3,
93, 255, 93, 255,
165, 252, 165, 252,
204, 5, 204, 5,
2, 251, 2, 251,
8, 1, 8, 1,
6, 4, 6, 4,
200, 248, 200, 248,
97, 6, 97, 6,
104, 254, 104, 254,
85, 251, 85, 251,
191, 8, 191, 8,
5, 248, 5, 248,
87, 2, 87, 2,
58, 5, 58, 5,
161, 245, 161, 245,
201, 9, 201, 9,
172, 252, 172, 252,
85, 250, 85, 250,
12, 12, 12, 12,
47, 244, 47, 244,
147, 4, 147, 4,
238, 5, 238, 5,
65, 242, 65, 242,
13, 14, 13, 14,
223, 249, 223, 249,
8, 250, 8, 250,
105, 15, 105, 15,
130, 239, 130, 239,
1, 8, 1, 8,
181, 5, 181, 5,
2, 239, 2, 239,
26, 19, 26, 19,
192, 245, 192, 245,
230, 250, 230, 250,
106, 18, 106, 18,
35, 234, 35, 234,
221, 12, 221, 12,
19, 4, 19, 4,
98, 236, 98, 236,
182, 24, 182, 24,
34, 240, 34, 240,
109, 253, 109, 253,
127, 20, 127, 20,
103, 228, 103, 228,
62, 19, 62, 19,
136, 0, 136, 0,
5, 235, 5, 235,
111, 30, 111, 30,
4, 233, 4, 233,
22, 2, 22, 2,
245, 20, 245, 20,
220, 222, 220, 222,
11, 27, 11, 27,
169, 250, 169, 250,
170, 235, 170, 235,
151, 35, 151, 35,
163, 224, 163, 224,
60, 9, 60, 9,
1, 19, 1, 19,
85, 218, 85, 218,
217, 35, 217, 35,
53, 242, 53, 242,
31, 239, 31, 239,
58, 39, 58, 39,
152, 215, 152, 215,
249, 18, 249, 18,
220, 13, 220, 13,
224, 215, 224, 215,
226, 44, 226, 44,
64, 231, 64, 231,
27, 246, 27, 246,
49, 40, 49, 40,
223, 206, 223, 206,
5, 31, 5, 31,
235, 4, 235, 4,
183, 216, 183, 216,
240, 52, 240, 52,
83, 218, 83, 218,
18, 1, 18, 1,
60, 37, 60, 37,
227, 199, 227, 199,
140, 44, 140, 44,
239, 247, 239, 247,
20, 222, 20, 222,
105, 58, 105, 58,
142, 204, 142, 204,
253, 15, 253, 15,
55, 29, 55, 29,
101, 196, 101, 196,
27, 58, 27, 58,
68, 231, 68, 231,
242, 232, 242, 232,
114, 59, 114, 59,
187, 191, 187, 191,
28, 34, 28, 34,
101, 15, 101, 15,
74, 198, 74, 198,
154, 69, 154, 69,
26, 212, 26, 212,
185, 249, 185, 249,
49, 54, 49, 54,
57, 182, 57, 182,
200, 53, 200, 53,
203, 251, 203, 251,
69, 207, 69, 207,
111, 76, 111, 76,
150, 192, 150, 192,
222, 15, 222, 15,
55, 41, 55, 41,
195, 178, 195, 178,
95, 72, 95, 72,
139, 227, 139, 227,
96, 224, 96, 224,
220, 75, 220, 75,
203, 175, 203, 175,
154, 41, 154, 41,
2, 20, 2, 20,
249, 183, 249, 183,
109, 86, 109, 86,
33, 201, 33, 201,
115, 249, 115, 249,
134, 65, 134, 65,
115, 165, 115, 165,
187, 67, 187, 67,
134, 247, 134, 247,
192, 199, 192, 199,
25, 92, 25, 92,
104, 176, 104, 176,
165, 24, 165, 24,
52, 44, 52, 44,
86, 165, 86, 165,
206, 89, 206, 89,
146, 214, 146, 214,
117, 226, 117, 226,
231, 85, 231, 85,
73, 158, 73, 158,
41, 58, 41, 58,
143, 12, 143, 12,
101, 178, 101, 178,
171, 102, 171, 102,
231, 181, 231, 181,
64, 6, 64, 6,
181, 65, 181, 65,
233, 151, 233, 151,
101, 88, 101, 88,
191, 229, 191, 229,
170, 205, 170, 205,
123, 101, 123, 101,
203, 155, 203, 155,
161, 46, 161, 46,
210, 31, 210, 31,
123, 161, 123, 161,
169, 108, 169, 108,
143, 189, 143, 189,
70, 245, 70, 245,
16, 83, 16, 83,
1, 143, 1, 143,
160, 84, 160, 84,
212, 243, 212, 243,
197, 188, 197, 188,
141, 112, 141, 112,
229, 155, 229, 155,
222, 35, 222, 35,
100, 47, 100, 47,
30, 149, 30, 149,
200, 111, 200, 111,
206, 196, 206, 196,
199, 231, 199, 231,
201, 95, 201, 95,
82, 137, 82, 137,
216, 80, 216, 80,
172, 254, 172, 254,
157, 176, 157, 176,
249, 119, 249, 119,
136, 156, 136, 156,
4, 28, 4, 28,
35, 58, 35, 58,
225, 140, 225, 140,
185, 113, 185, 113,
150, 201, 150, 201,
28, 223, 28, 223,
226, 103, 226, 103,
145, 133, 145, 133,
233, 78, 233, 78,
209, 4, 209, 4,
140, 169, 140, 169,
159, 124, 159, 124,
30, 156, 30, 156,
140, 24, 140, 24,
112, 63, 112, 63,
80, 136, 80, 136,
189, 115, 189, 115,
139, 202, 139, 202,
21, 220, 21, 220,
113, 107, 113, 107,
225, 130, 225, 130,
251, 79, 251, 79,
99, 5, 99, 5,
200, 167, 200, 167,
248, 126, 248, 126,
202, 153, 202, 153,
70, 26, 70, 26,
225, 62, 225, 62,
73, 135, 73, 135,
87, 118, 87, 118,
11, 199, 11, 199,
40, 223, 40, 223,
79, 106, 79, 106,
25, 129, 25, 129,
104, 84, 104, 84,
0, 0, 0, 0,
159, 171, 159, 171,
220, 126, 220, 126,
138, 149, 138, 149,
94, 33, 94, 33,
38, 56, 38, 56,
50, 138, 50, 138,
48, 121, 48, 121,
60, 191, 60, 191,
129, 232, 129, 232,
1, 100, 1, 100,
223, 128, 223, 128,
167, 91, 167, 91,
198, 244, 198, 244,
126, 181, 126, 181,
113, 123, 113, 123,
74, 144, 74, 144,
74, 45, 74, 45,
19, 43, 19, 43,
238, 145, 238, 145,
7, 123, 7, 123,
34, 180, 34, 180,
224, 247, 224, 247,
205, 87, 205, 87,
162, 131, 162, 131,
60, 100, 60, 100,
133, 228, 133, 228,
184, 197, 184, 197,
78, 115, 78, 115,
229, 139, 229, 139,
158, 60, 158, 60,
233, 23, 233, 23,
156, 159, 156, 159,
212, 121, 212, 121,
189, 167, 189, 167,
75, 12, 75, 12,
27, 69, 27, 69,
85, 139, 85, 139,
184, 107, 184, 107,
252, 208, 252, 208,
36, 220, 36, 220,
229, 100, 229, 100,
250, 138, 250, 138,
231, 76, 231, 76,
190, 255, 190, 255,
27, 180, 27, 180,
27, 115, 27, 115,
6, 157, 6, 157,
183, 35, 183, 35,
6, 44, 6, 44,
241, 153, 241, 153,
239, 110, 239, 110,
17, 189, 17, 189,
132, 247, 132, 247,
32, 79, 32, 79,
128, 144, 128, 144,
166, 90, 166, 90,
243, 228, 243, 228,
79, 207, 79, 207,
146, 100, 146, 100,
169, 151, 169, 151,
197, 58, 197, 58,
4, 14, 4, 14,
165, 176, 165, 176,
135, 106, 135, 106,
197, 172, 197, 172,
14, 21, 14, 21,
62, 50, 62, 50,
242, 158, 242, 158,
185, 97, 185, 97,
109, 203, 109, 203,
99, 239, 99, 239,
23, 77, 23, 77,
77, 155, 77, 155,
237, 76, 237, 76,
107, 238, 107, 238,
224, 206, 224, 206,
247, 91, 247, 91,
165, 164, 165, 164,
64, 48, 64, 48,
160, 16, 160, 16,
54, 183, 54, 183,
75, 94, 75, 94,
65, 184, 65, 184,
80, 16, 80, 16,
194, 45, 194, 45,
89, 170, 89, 170,
75, 85, 75, 85,
109, 210, 109, 210,
130, 241, 130, 241,
210, 66, 210, 66,
137, 168, 137, 168,
126, 67, 126, 67,
34, 239, 34, 239,
108, 215, 108, 215,
83, 78, 83, 78,
140, 176, 140, 176,
41, 44, 41, 44,
166, 10, 166, 10,
124, 196, 124, 196,
53, 80, 53, 80,
31, 192, 31, 192,
191, 18, 191, 18,
251, 33, 251, 33,
221, 185, 221, 185,
157, 73, 157, 73,
110, 212, 110, 212,
102, 250, 102, 250,
35, 51, 35, 51,
133, 183, 133, 183,
131, 60, 131, 60,
140, 234, 140, 234,
154, 229, 154, 229,
49, 61, 49, 61,
116, 188, 116, 188,
76, 43, 76, 43,
218, 255, 218, 255,
0, 214, 0, 214,
50, 64, 50, 64,
255, 198, 255, 198,
105, 24, 105, 24,
68, 18, 68, 18,
94, 204, 94, 204,
254, 60, 254, 60,
41, 213, 41, 213,
11, 6, 11, 6,
106, 32, 106, 32,
169, 200, 169, 200,
245, 52, 245, 52,
235, 228, 235, 228,
236, 245, 236, 245,
166, 41, 166, 41,
53, 202, 53, 202,
183, 41, 183, 41,
118, 244, 118, 244,
51, 233, 51, 233,
247, 45, 247, 45,
232, 207, 232, 207,
237, 28, 237, 28,
90, 2, 90, 2,
114, 224, 114, 224,
225, 45, 225, 45,
114, 216, 114, 216,
21, 16, 21, 16,
157, 13, 157, 13,
182, 219, 182, 219,
64, 42, 64, 42,
122, 226, 122, 226,
93, 4, 93, 4,
190, 21, 190, 21,
159, 218, 159, 218,
31, 36, 31, 36,
204, 236, 204, 236,
155, 250, 155, 250,
166, 26, 166, 26,
134, 220, 134, 220,
143, 28, 143, 28,
108, 246, 108, 246,
66, 243, 66, 243,
149, 28, 149, 28,
154, 224, 154, 224,
140, 20, 140, 20,
167, 254, 167, 254,
114, 238, 114, 238,
6, 28, 6, 28,
6, 230, 6, 230,
226, 12, 226, 12,
21, 5, 21, 5,
4, 236, 4, 236,
152, 25, 152, 25,
1, 236, 1, 236,
41, 6, 41, 6,
144, 9, 144, 9,
159, 235, 159, 235,
240, 21, 240, 21,
228, 241, 228, 241,
188, 0, 188, 0,
45, 12, 45, 12,
208, 236, 208, 236,
173, 17, 173, 17,
50, 247, 50, 247,
195, 252, 195, 252,
39, 13, 39, 13,
21, 239, 21, 239,
84, 13, 84, 13,
154, 251, 154, 251,
57, 250, 57, 250,
212, 12, 212, 12,
246, 241, 246, 241,
77, 9, 77, 9,
245, 254, 245, 254,
246, 248, 246, 248,
147, 11, 147, 11,
8, 245, 8, 245,
220, 5, 220, 5,
63, 1, 63, 1,
190, 248, 190, 248,
194, 9, 194, 9,
247, 247, 247, 247,
40, 3, 40, 3,
145, 2, 145, 2,
74, 249, 74, 249,
181, 7, 181, 7,
137, 250, 137, 250,
56, 1, 56, 1,
20, 3, 20, 3,
84, 250, 84, 250,
174, 5, 174, 5,
155, 252, 155, 252,
0, 0, 0, 0,
252, 2, 252, 2,
153, 251, 153, 251,
223, 3, 223, 3,
35, 254, 35, 254,
98, 255, 98, 255,
127, 2, 127, 2,
227, 252, 227, 252,
100, 2, 100, 2,
39, 255, 39, 255,
56, 255, 56, 255,
209, 1, 209, 1,
11, 254, 11, 254,
76, 1, 76, 1,
187, 255, 187, 255,
88, 255, 88, 255,
29, 1, 29, 1,
246, 254, 246, 254,
147, 0, 147, 0,
252, 255, 252, 255,
155, 255, 155, 255,
134, 0, 134, 0,
151, 255, 151, 255,
45, 0, 45, 0,
8, 0, 8, 0,
220, 255, 220, 255,
34, 0, 34, 0,
236, 255, 236, 255,
4, 0, 4, 0,
1, 0, 1, 0,
254, 255, 254, 255,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
};
auto cfg = kit.defaultConfig(AudioOutput);
void setup() {
  LOGLEVEL_AUDIOKIT = AudioKitDebug; 
  Serial.begin(115200);
  // open in write mode
  
  kit.begin(cfg);
  //


}
uint32_t times;
void loop() {
  
  if(micros()-times>=170000){
  size_t bytes_written = 0;
  i2s_write(cfg.i2s_num, wav_array8bit, WAV_SIZE, &bytes_written, portMAX_DELAY);
  Serial.print("bytes_writen: ");Serial.println(bytes_written);

  times=micros();
  }
  
}