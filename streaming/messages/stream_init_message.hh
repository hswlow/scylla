/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Modified by Cloudius Systems.
 * Copyright 2015 Cloudius Systems.
 */

#pragma once

#include "core/sstring.hh"
#include "bytes.hh"
#include "gms/inet_address.hh"
#include "utils/UUID.hh"

namespace streaming {
namespace messages {


/**
 * StreamInitMessage is first sent from the node where {@link org.apache.cassandra.streaming.StreamSession} is started,
 * to initiate corresponding {@link org.apache.cassandra.streaming.StreamSession} on the other side.
 */
class stream_init_message {
public:
    using inet_address = gms::inet_address;
    using UUID = utils::UUID;
    inet_address from;
    int session_index;
    UUID plan_id;
    sstring description;

    // true if this init message is to connect for outgoing message on receiving side
    bool is_for_outgoing;
    bool keep_ss_table_level;

    stream_init_message() = default;

    stream_init_message(inet_address _from, int _session_index, UUID _plan_id, sstring _description, bool _is_for_outgoing, bool _keep_ss_table_level)
        : from(_from)
        , session_index(_session_index)
        , plan_id(_plan_id)
        , description(_description)
        , is_for_outgoing(_is_for_outgoing)
        , keep_ss_table_level(-keep_ss_table_level) {
    }

#if 0
    /**
     * Create serialized message.
     *
     * @param compress true if message is compressed
     * @param version Streaming protocol version
     * @return serialized message in ByteBuffer format
     */
    public ByteBuffer createMessage(boolean compress, int version)
    {
        int header = 0;
        // set compression bit.
        if (compress)
            header |= 4;
        // set streaming bit
        header |= 8;
        // Setting up the version bit
        header |= (version << 8);

        byte[] bytes;
        try
        {
            int size = (int)StreamInitMessage.serializer.serializedSize(this, version);
            DataOutputBuffer buffer = new DataOutputBuffer(size);
            StreamInitMessage.serializer.serialize(this, buffer, version);
            bytes = buffer.getData();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
        assert bytes.length > 0;

        ByteBuffer buffer = ByteBuffer.allocate(4 + 4 + bytes.length);
        buffer.putInt(MessagingService.PROTOCOL_MAGIC);
        buffer.putInt(header);
        buffer.put(bytes);
        buffer.flip();
        return buffer;
    }

    private static class StreamInitMessageSerializer implements IVersionedSerializer<StreamInitMessage>
    {
        public void serialize(StreamInitMessage message, DataOutputPlus out, int version) throws IOException
        {
            CompactEndpointSerializationHelper.serialize(message.from, out);
            out.writeInt(message.sessionIndex);
            UUIDSerializer.serializer.serialize(message.planId, out, MessagingService.current_version);
            out.writeUTF(message.description);
            out.writeBoolean(message.isForOutgoing);
            out.writeBoolean(message.keepSSTableLevel);
        }

        public StreamInitMessage deserialize(DataInput in, int version) throws IOException
        {
            InetAddress from = CompactEndpointSerializationHelper.deserialize(in);
            int sessionIndex = in.readInt();
            UUID planId = UUIDSerializer.serializer.deserialize(in, MessagingService.current_version);
            String description = in.readUTF();
            boolean sentByInitiator = in.readBoolean();
            boolean keepSSTableLevel = in.readBoolean();
            return new StreamInitMessage(from, sessionIndex, planId, description, sentByInitiator, keepSSTableLevel);
        }

        public long serializedSize(StreamInitMessage message, int version)
        {
            long size = CompactEndpointSerializationHelper.serializedSize(message.from);
            size += TypeSizes.NATIVE.sizeof(message.sessionIndex);
            size += UUIDSerializer.serializer.serializedSize(message.planId, MessagingService.current_version);
            size += TypeSizes.NATIVE.sizeof(message.description);
            size += TypeSizes.NATIVE.sizeof(message.isForOutgoing);
            size += TypeSizes.NATIVE.sizeof(message.keepSSTableLevel);
            return size;
        }
    }
#endif
public:
    void serialize(bytes::iterator& out) const {
    }
    static stream_init_message deserialize(bytes_view& v) {
        return stream_init_message();
    }
    size_t serialized_size() const {
        return 0;
    }
};

} // namespace messages
} // namespace streaming
