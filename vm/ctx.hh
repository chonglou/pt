#include <cassert>

namespace pt {
	class vm_ctx {
		public:
			vm_ctx(int r) { 
				assert(r > 1 && r <= 10);
				radix=r;
			}
			inline int getradix(void) {
				return radix;
			}
		private:
			int radix;
	};
}


