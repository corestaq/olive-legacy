#ifndef TRANSITIONBLOCK_H
#define TRANSITIONBLOCK_H

#include "node/block/block.h"

class TransitionBlock : public Block
{
public:
  TransitionBlock();

  virtual Type type() const override;

  NodeInput* out_block_input() const;
  NodeInput* in_block_input() const;

  virtual void Retranslate() override;

  rational in_offset() const;
  rational out_offset() const;

private:
  NodeInput* out_block_input_;

  NodeInput* in_block_input_;

  Block* connected_out_block_;

  Block* connected_in_block_;

};

#endif // TRANSITIONBLOCK_H
